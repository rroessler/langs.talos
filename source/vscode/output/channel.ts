/// Vendor Modules
import * as vscode from 'vscode';

/// Talos Modules
import { Product } from '@/talos/product';

/** Output Channel Factory. */
export interface Channel extends vscode.OutputChannel {}
export const Channel = (label?: string) =>
    vscode.window.createOutputChannel(`${Product.shortName}${label ? ' - ' : ''}${label ?? ''}`, Product.identifier);
